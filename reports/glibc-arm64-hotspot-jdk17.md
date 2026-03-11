---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ❌ FAIL

**Date:** 2026-03-11 05:23:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 8 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 2 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1773220737 24
1773220742 24
1773220747 24
1773220752 24
1773220757 24
1773220762 24
1773220767 24
1773220772 24
1773220777 24
1773220782 24
1773220787 24
1773220792 24
1773220797 24
1773220802 24
1773220807 24
1773220812 24
1773220817 24
1773220822 24
1773220827 24
1773220832 24
```
</details>

---

