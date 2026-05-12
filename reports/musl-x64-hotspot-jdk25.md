---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-12 02:56:29 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1778568781 48
1778568786 48
1778568791 48
1778568796 48
1778568801 43
1778568806 43
1778568811 43
1778568816 43
1778568821 43
1778568826 43
1778568831 43
1778568836 43
1778568841 43
1778568846 43
1778568851 43
1778568856 43
1778568861 43
1778568866 43
1778568871 43
1778568876 43
```
</details>

---

