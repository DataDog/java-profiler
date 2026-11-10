---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 10:42:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (5 unique values: 66-73 cores)</summary>

```
1794324980 66
1794324985 66
1794324990 69
1794324995 69
1794325000 69
1794325005 69
1794325010 69
1794325015 69
1794325020 69
1794325025 69
1794325030 69
1794325035 69
1794325040 69
1794325045 71
1794325050 71
1794325055 71
1794325060 71
1794325065 71
1794325070 71
1794325075 71
```
</details>

---

