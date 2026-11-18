---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:38:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
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
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1795001611 51
1795001616 51
1795001621 51
1795001626 51
1795001631 51
1795001636 51
1795001641 51
1795001646 51
1795001651 51
1795001656 51
1795001661 51
1795001666 51
1795001671 51
1795001676 51
1795001681 51
1795001686 64
1795001691 64
1795001696 64
1795001701 64
1795001706 64
```
</details>

---

