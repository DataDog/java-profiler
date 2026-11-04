---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 17:22:56 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 7 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1793830727 48
1793830732 48
1793830737 48
1793830742 48
1793830747 48
1793830752 48
1793830757 48
1793830762 48
1793830767 48
1793830772 48
1793830777 48
1793830782 48
1793830787 48
1793830792 48
1793830797 48
1793830802 48
1793830807 48
1793830812 48
1793830817 48
1793830822 48
```
</details>

---

