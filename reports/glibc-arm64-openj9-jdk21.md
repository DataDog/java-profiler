---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 07:41:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 315 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 40-45 cores)</summary>

```
1794832708 45
1794832713 45
1794832718 45
1794832723 45
1794832728 45
1794832733 45
1794832738 45
1794832743 45
1794832748 45
1794832753 45
1794832758 45
1794832763 45
1794832768 45
1794832773 45
1794832778 45
1794832783 45
1794832788 45
1794832793 45
1794832798 40
1794832803 40
```
</details>

---

