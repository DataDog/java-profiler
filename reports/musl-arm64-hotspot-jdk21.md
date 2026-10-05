---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-05 11:49:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1791215053 48
1791215058 48
1791215063 48
1791215068 46
1791215073 46
1791215078 46
1791215083 46
1791215088 41
1791215093 41
1791215098 41
1791215103 41
1791215108 41
1791215113 41
1791215118 41
1791215123 41
1791215128 41
1791215133 41
1791215138 41
1791215143 41
1791215148 43
```
</details>

---

