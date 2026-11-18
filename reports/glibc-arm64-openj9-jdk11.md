---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:10:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 369 |
| Sample Rate | 6.15/sec |
| Health Score | 384% |
| Threads | 12 |
| Allocations | 184 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 169 |
| Sample Rate | 2.82/sec |
| Health Score | 176% |
| Threads | 14 |
| Allocations | 95 |

<details>
<summary>CPU Timeline (3 unique values: 34-52 cores)</summary>

```
1795010728 34
1795010733 34
1795010738 34
1795010743 34
1795010748 34
1795010753 34
1795010758 34
1795010763 34
1795010768 39
1795010773 39
1795010778 52
1795010783 52
1795010788 52
1795010793 52
1795010798 52
1795010803 52
1795010808 52
1795010813 52
1795010818 52
1795010823 52
```
</details>

---

