---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-18 02:29:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 197 |
| Sample Rate | 3.28/sec |
| Health Score | 205% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 209 |
| Sample Rate | 3.48/sec |
| Health Score | 217% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 54-74 cores)</summary>

```
1789712725 54
1789712730 54
1789712735 54
1789712740 74
1789712745 74
1789712750 74
1789712755 74
1789712760 74
1789712765 74
1789712770 74
1789712775 74
1789712780 74
1789712785 74
1789712790 74
1789712795 74
1789712800 74
1789712805 74
1789712810 74
1789712815 74
1789712820 74
```
</details>

---

