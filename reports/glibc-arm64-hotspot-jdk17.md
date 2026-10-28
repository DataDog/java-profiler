---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 01:05:53 EDT

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
| CPU Cores (start) | 9 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1793163657 9
1793163662 9
1793163667 9
1793163672 9
1793163677 9
1793163682 9
1793163687 9
1793163692 9
1793163697 9
1793163702 9
1793163707 9
1793163712 9
1793163717 9
1793163722 9
1793163727 9
1793163732 9
1793163737 9
1793163742 9
1793163747 9
1793163752 9
```
</details>

---

