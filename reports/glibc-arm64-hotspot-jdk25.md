---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-24 13:07:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 44 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 8 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 56-64 cores)</summary>

```
1787590937 64
1787590942 64
1787590947 64
1787590952 64
1787590957 64
1787590962 64
1787590967 64
1787590972 64
1787590977 64
1787590982 64
1787590987 64
1787590992 61
1787590997 61
1787591002 61
1787591007 61
1787591012 61
1787591017 61
1787591022 61
1787591027 61
1787591032 61
```
</details>

---

