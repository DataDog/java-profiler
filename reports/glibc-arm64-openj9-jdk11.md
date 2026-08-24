---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ❌ FAIL

**Date:** 2026-08-24 13:07:02 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 10 |
| Allocations | 222 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 178 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1787590937 48
1787590942 48
1787590947 48
1787590952 48
1787590957 48
1787590962 48
1787590967 48
1787590972 48
1787590977 48
1787590982 48
1787590987 48
1787590992 48
1787590997 48
1787591002 48
1787591007 48
1787591012 48
1787591017 48
1787591022 48
1787591027 48
1787591032 48
```
</details>

---

