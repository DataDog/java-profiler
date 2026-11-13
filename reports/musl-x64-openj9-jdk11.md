---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 06:08:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 889 |
| Sample Rate | 14.82/sec |
| Health Score | 926% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 19-24 cores)</summary>

```
1794567778 22
1794567783 22
1794567788 22
1794567793 22
1794567798 22
1794567803 22
1794567808 22
1794567813 22
1794567818 22
1794567823 24
1794567828 24
1794567833 19
1794567838 19
1794567843 19
1794567848 19
1794567853 19
1794567858 19
1794567863 19
1794567868 19
1794567873 19
```
</details>

---

