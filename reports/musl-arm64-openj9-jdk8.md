---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-02 13:35:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 320 |
| Sample Rate | 5.33/sec |
| Health Score | 333% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1788369935 48
1788369940 48
1788369945 48
1788369950 48
1788369955 48
1788369960 48
1788369965 48
1788369970 48
1788369975 48
1788369980 48
1788369985 48
1788369990 48
1788369995 48
1788370000 48
1788370005 48
1788370010 48
1788370015 48
1788370020 48
1788370025 48
1788370030 48
```
</details>

---

