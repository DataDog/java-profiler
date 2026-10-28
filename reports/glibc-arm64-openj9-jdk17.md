---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 01:05:53 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 299 |
| Sample Rate | 4.98/sec |
| Health Score | 311% |
| Threads | 9 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793163650 43
1793163655 43
1793163660 43
1793163665 43
1793163670 43
1793163675 48
1793163680 48
1793163685 48
1793163690 48
1793163695 48
1793163701 48
1793163706 48
1793163711 48
1793163716 48
1793163721 48
1793163726 48
1793163731 48
1793163736 48
1793163741 48
1793163746 48
```
</details>

---

