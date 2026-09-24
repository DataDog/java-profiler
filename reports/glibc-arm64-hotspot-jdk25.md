---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 15:41:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790278718 48
1790278723 48
1790278728 48
1790278733 48
1790278738 48
1790278743 48
1790278748 48
1790278753 48
1790278758 48
1790278763 48
1790278768 48
1790278773 48
1790278778 48
1790278783 48
1790278788 48
1790278793 48
1790278798 48
1790278803 48
1790278808 48
1790278813 48
```
</details>

---

