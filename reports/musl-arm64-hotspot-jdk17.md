---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-20 06:11:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (4 unique values: 44-47 cores)</summary>

```
1792490688 46
1792490693 44
1792490698 44
1792490703 44
1792490708 44
1792490713 44
1792490718 44
1792490723 44
1792490728 44
1792490733 46
1792490738 46
1792490743 47
1792490748 47
1792490753 47
1792490758 46
1792490763 46
1792490768 47
1792490773 47
1792490778 46
1792490783 46
```
</details>

---

