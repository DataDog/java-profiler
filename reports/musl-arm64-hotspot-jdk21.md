---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 02:32:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 8 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 10 |
| Allocations | 140 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789712710 38
1789712715 38
1789712720 43
1789712725 43
1789712730 48
1789712735 48
1789712740 48
1789712745 48
1789712750 48
1789712755 48
1789712760 48
1789712765 48
1789712770 48
1789712775 48
1789712780 48
1789712785 48
1789712790 48
1789712795 48
1789712800 48
1789712805 48
```
</details>

---

