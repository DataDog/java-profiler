---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:34:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 14 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 21-26 cores)</summary>

```
1795015805 21
1795015810 21
1795015815 21
1795015820 26
1795015825 26
1795015830 21
1795015835 21
1795015840 21
1795015845 21
1795015850 21
1795015855 21
1795015860 21
1795015865 21
1795015870 21
1795015875 21
1795015880 21
1795015885 21
1795015890 26
1795015895 26
1795015900 21
```
</details>

---

