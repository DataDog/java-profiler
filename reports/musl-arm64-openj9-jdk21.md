---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-17 05:46:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1786959750 48
1786959755 48
1786959760 48
1786959765 48
1786959770 48
1786959775 48
1786959780 48
1786959785 48
1786959790 48
1786959795 48
1786959800 43
1786959805 43
1786959810 42
1786959815 42
1786959820 42
1786959825 42
1786959830 42
1786959835 42
1786959840 42
1786959846 42
```
</details>

---

