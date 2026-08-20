---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 06:18:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 13 |
| Allocations | 164 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787220875 43
1787220880 43
1787220885 43
1787220890 43
1787220895 43
1787220900 48
1787220905 48
1787220910 48
1787220915 48
1787220920 48
1787220925 48
1787220930 48
1787220935 48
1787220940 48
1787220945 48
1787220950 48
1787220955 48
1787220960 48
1787220965 48
1787220970 48
```
</details>

---

