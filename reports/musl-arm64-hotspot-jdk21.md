---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 17:22:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (4 unique values: 36-48 cores)</summary>

```
1793830727 36
1793830732 36
1793830737 36
1793830742 36
1793830747 36
1793830752 36
1793830757 36
1793830762 43
1793830767 43
1793830772 43
1793830777 43
1793830782 48
1793830787 48
1793830792 48
1793830797 48
1793830802 48
1793830807 48
1793830812 48
1793830817 48
1793830822 46
```
</details>

---

