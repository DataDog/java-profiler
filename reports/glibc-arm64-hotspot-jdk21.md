---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 10:29:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1792679071 46
1792679076 41
1792679081 41
1792679086 41
1792679091 41
1792679096 41
1792679101 41
1792679106 41
1792679111 41
1792679116 41
1792679121 41
1792679126 41
1792679131 41
1792679136 41
1792679141 41
1792679146 46
1792679151 46
1792679156 46
1792679161 46
1792679166 46
```
</details>

---

