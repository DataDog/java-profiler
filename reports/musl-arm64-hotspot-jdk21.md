---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 09:57:28 EDT

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
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 11 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 953 |
| Sample Rate | 15.88/sec |
| Health Score | 993% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1792677073 48
1792677078 48
1792677083 48
1792677088 48
1792677093 48
1792677098 48
1792677103 48
1792677108 48
1792677113 48
1792677118 48
1792677123 48
1792677128 48
1792677133 48
1792677138 48
1792677143 53
1792677148 53
1792677153 53
1792677158 53
1792677163 53
1792677168 53
```
</details>

---

