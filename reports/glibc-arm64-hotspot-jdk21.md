---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 11:49:13 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1794501758 48
1794501763 48
1794501768 48
1794501773 48
1794501778 48
1794501783 48
1794501788 48
1794501793 48
1794501799 48
1794501804 48
1794501809 48
1794501814 48
1794501819 48
1794501824 48
1794501829 48
1794501834 48
1794501839 48
1794501844 43
1794501849 43
1794501854 38
```
</details>

---

