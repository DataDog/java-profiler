---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 11:55:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793288984 48
1793288989 48
1793288994 48
1793288999 48
1793289004 48
1793289009 48
1793289014 48
1793289019 48
1793289024 48
1793289029 48
1793289034 48
1793289039 48
1793289044 48
1793289049 48
1793289054 48
1793289059 48
1793289064 48
1793289069 48
1793289074 48
1793289079 48
```
</details>

---

