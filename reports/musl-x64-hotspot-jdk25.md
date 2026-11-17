---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 10:58:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1794930701 49
1794930706 49
1794930711 49
1794930716 49
1794930721 49
1794930726 49
1794930731 49
1794930736 49
1794930741 49
1794930746 49
1794930751 49
1794930756 51
1794930761 51
1794930766 51
1794930771 51
1794930776 51
1794930781 51
1794930786 51
1794930791 51
1794930796 51
```
</details>

---

