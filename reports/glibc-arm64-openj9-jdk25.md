---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-20 08:51:01 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 9 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 23-48 cores)</summary>

```
1787229997 23
1787230002 43
1787230007 43
1787230012 48
1787230017 48
1787230022 48
1787230027 48
1787230032 48
1787230037 48
1787230042 48
1787230047 48
1787230052 48
1787230057 48
1787230062 48
1787230067 48
1787230072 48
1787230077 48
1787230082 48
1787230087 48
1787230092 48
```
</details>

---

