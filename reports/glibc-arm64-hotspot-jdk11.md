---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 10:17:16 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 216 |
| Sample Rate | 3.60/sec |
| Health Score | 225% |
| Threads | 10 |
| Allocations | 169 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 8 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (4 unique values: 44-48 cores)</summary>

```
1793196648 45
1793196653 45
1793196658 45
1793196663 45
1793196668 45
1793196673 45
1793196678 45
1793196683 44
1793196688 44
1793196693 44
1793196698 44
1793196703 47
1793196708 47
1793196713 47
1793196718 47
1793196723 48
1793196728 48
1793196733 48
1793196738 48
1793196743 48
```
</details>

---

