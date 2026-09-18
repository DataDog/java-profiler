---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-18 09:29:08 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 63-74 cores)</summary>

```
1789737725 65
1789737730 65
1789737735 65
1789737740 65
1789737745 63
1789737750 63
1789737755 63
1789737760 63
1789737765 63
1789737770 63
1789737775 63
1789737780 63
1789737785 69
1789737790 69
1789737795 69
1789737800 69
1789737805 69
1789737810 69
1789737815 69
1789737820 74
```
</details>

---

