---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 06:07:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 11 |
| Allocations | 422 |

<details>
<summary>CPU Timeline (5 unique values: 71-93 cores)</summary>

```
1794827051 80
1794827056 77
1794827061 77
1794827066 77
1794827071 77
1794827076 85
1794827081 85
1794827086 85
1794827091 85
1794827096 85
1794827101 85
1794827106 85
1794827111 85
1794827116 85
1794827121 85
1794827126 85
1794827131 93
1794827136 93
1794827141 93
1794827146 93
```
</details>

---

