---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-18 21:23:44 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 9 |
| Allocations | 124 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 3.83/sec |
| Health Score | 239% |
| Threads | 10 |
| Allocations | 171 |

<details>
<summary>CPU Timeline (3 unique values: 36-40 cores)</summary>

```
1792372754 36
1792372759 36
1792372764 36
1792372769 36
1792372774 36
1792372779 36
1792372784 36
1792372789 36
1792372794 38
1792372799 38
1792372804 38
1792372809 38
1792372814 38
1792372819 38
1792372824 38
1792372829 38
1792372834 38
1792372839 38
1792372844 38
1792372849 38
```
</details>

---

