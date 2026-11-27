---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 08:43:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (4 unique values: 82-91 cores)</summary>

```
1795786753 82
1795786758 82
1795786763 82
1795786768 82
1795786773 82
1795786778 82
1795786783 82
1795786788 82
1795786793 82
1795786798 91
1795786803 91
1795786808 91
1795786813 91
1795786818 89
1795786823 89
1795786828 89
1795786833 89
1795786838 89
1795786843 89
1795786848 88
```
</details>

---

