---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 13:36:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 18-32 cores)</summary>

```
1794594668 18
1794594673 18
1794594678 18
1794594683 18
1794594688 18
1794594693 18
1794594698 18
1794594703 18
1794594708 18
1794594713 18
1794594718 18
1794594723 18
1794594728 32
1794594733 32
1794594738 32
1794594743 32
1794594748 30
1794594753 30
1794594758 30
1794594763 30
```
</details>

---

