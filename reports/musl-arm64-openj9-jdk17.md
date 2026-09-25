---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-25 06:34:10 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 12 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790332032 44
1790332037 44
1790332042 43
1790332047 43
1790332052 43
1790332057 43
1790332062 43
1790332067 43
1790332072 43
1790332077 43
1790332082 44
1790332087 44
1790332093 44
1790332098 44
1790332103 44
1790332108 44
1790332113 48
1790332118 48
1790332123 48
1790332128 48
```
</details>

---

