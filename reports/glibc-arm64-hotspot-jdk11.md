---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-14 10:08:53 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 12 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 15 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (4 unique values: 49-64 cores)</summary>

```
1791986638 49
1791986643 49
1791986648 49
1791986653 54
1791986658 54
1791986663 49
1791986668 49
1791986673 49
1791986678 49
1791986683 49
1791986688 49
1791986693 49
1791986698 49
1791986703 49
1791986708 59
1791986713 59
1791986718 64
1791986723 64
1791986728 64
1791986733 64
```
</details>

---

