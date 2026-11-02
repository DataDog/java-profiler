---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 10:41:18 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 39-44 cores)</summary>

```
1793633751 42
1793633756 42
1793633761 42
1793633766 42
1793633771 44
1793633776 44
1793633781 44
1793633786 44
1793633791 44
1793633796 44
1793633801 44
1793633806 44
1793633811 44
1793633816 44
1793633821 44
1793633826 44
1793633831 44
1793633836 44
1793633841 44
1793633846 44
```
</details>

---

