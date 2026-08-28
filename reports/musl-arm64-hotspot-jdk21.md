---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-28 08:25:45 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 312 |
| Sample Rate | 5.20/sec |
| Health Score | 325% |
| Threads | 14 |
| Allocations | 161 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1787919693 48
1787919698 48
1787919703 48
1787919708 48
1787919713 40
1787919718 40
1787919723 40
1787919728 40
1787919733 40
1787919738 40
1787919743 40
1787919748 40
1787919753 40
1787919758 40
1787919763 40
1787919768 40
1787919773 40
1787919778 40
1787919783 40
1787919788 40
```
</details>

---

