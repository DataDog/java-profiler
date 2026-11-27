---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 08:24:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 10 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795785620 64
1795785625 64
1795785630 64
1795785635 64
1795785640 64
1795785645 64
1795785650 48
1795785655 48
1795785660 48
1795785665 48
1795785670 48
1795785675 48
1795785680 48
1795785685 48
1795785690 48
1795785695 48
1795785700 48
1795785705 48
1795785710 48
1795785715 48
```
</details>

---

