---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 11:02:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (5 unique values: 86-90 cores)</summary>

```
1793635036 89
1793635041 89
1793635046 89
1793635051 89
1793635056 89
1793635061 89
1793635066 89
1793635071 89
1793635076 88
1793635081 88
1793635086 88
1793635091 88
1793635096 88
1793635101 88
1793635106 88
1793635111 88
1793635116 88
1793635121 88
1793635126 90
1793635131 90
```
</details>

---

