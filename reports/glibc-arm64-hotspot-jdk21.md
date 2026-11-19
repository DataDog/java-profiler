---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:30:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (6 unique values: 37-45 cores)</summary>

```
1795112653 40
1795112658 40
1795112663 40
1795112668 40
1795112673 40
1795112678 39
1795112683 39
1795112688 37
1795112693 37
1795112698 37
1795112703 37
1795112708 42
1795112713 42
1795112718 42
1795112723 42
1795112728 43
1795112733 43
1795112738 43
1795112743 43
1795112748 43
```
</details>

---

