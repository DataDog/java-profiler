---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-25 11:33:43 EDT

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 12 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 987 |
| Sample Rate | 16.45/sec |
| Health Score | 1028% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787671682 64
1787671687 64
1787671692 64
1787671697 64
1787671702 64
1787671707 64
1787671712 64
1787671717 64
1787671722 64
1787671727 64
1787671732 64
1787671737 64
1787671742 64
1787671747 64
1787671752 64
1787671757 64
1787671762 64
1787671767 64
1787671772 64
1787671777 64
```
</details>

---

