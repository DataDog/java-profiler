---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 05:56:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 13 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1793616780 14
1793616785 14
1793616790 14
1793616795 14
1793616800 14
1793616805 14
1793616810 14
1793616815 14
1793616820 14
1793616825 14
1793616830 14
1793616835 14
1793616840 14
1793616845 14
1793616850 14
1793616855 14
1793616860 14
1793616865 14
1793616870 14
1793616875 9
```
</details>

---

