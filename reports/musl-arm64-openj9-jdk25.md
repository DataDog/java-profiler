---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 00:48:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790570656 43
1790570661 43
1790570666 43
1790570671 43
1790570676 43
1790570681 43
1790570686 43
1790570691 43
1790570696 43
1790570701 43
1790570706 48
1790570711 48
1790570716 48
1790570721 48
1790570726 48
1790570731 48
1790570736 48
1790570742 48
1790570747 48
1790570752 48
```
</details>

---

