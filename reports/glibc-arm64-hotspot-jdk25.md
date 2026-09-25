---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-25 08:26:13 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 14 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 42-44 cores)</summary>

```
1790338718 42
1790338723 44
1790338728 44
1790338733 44
1790338738 44
1790338743 44
1790338748 44
1790338753 44
1790338758 44
1790338763 44
1790338768 44
1790338773 44
1790338778 44
1790338783 44
1790338788 44
1790338793 44
1790338798 44
1790338803 44
1790338808 44
1790338813 44
```
</details>

---

