---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-25 08:54:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 830 |
| Sample Rate | 13.83/sec |
| Health Score | 864% |
| Threads | 8 |
| Allocations | 320 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 948 |
| Sample Rate | 15.80/sec |
| Health Score | 988% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 79-96 cores)</summary>

```
1792932545 79
1792932550 79
1792932555 79
1792932560 79
1792932565 79
1792932570 79
1792932575 79
1792932580 79
1792932585 79
1792932590 79
1792932595 79
1792932600 79
1792932605 79
1792932610 79
1792932615 96
1792932620 96
1792932625 96
1792932630 96
1792932635 96
1792932640 96
```
</details>

---

