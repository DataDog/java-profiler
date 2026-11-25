---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 12:18:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 306 |
| Sample Rate | 5.10/sec |
| Health Score | 319% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 273 |
| Sample Rate | 4.55/sec |
| Health Score | 284% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 46-52 cores)</summary>

```
1795626745 52
1795626750 52
1795626755 52
1795626760 52
1795626765 52
1795626770 52
1795626775 52
1795626780 46
1795626785 46
1795626790 46
1795626795 46
1795626800 46
1795626805 46
1795626810 46
1795626815 46
1795626820 46
1795626825 46
1795626830 46
1795626835 46
1795626840 46
```
</details>

---

