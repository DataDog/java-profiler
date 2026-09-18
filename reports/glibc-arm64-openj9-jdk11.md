---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:37:49 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 11 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 157 |
| Sample Rate | 2.62/sec |
| Health Score | 164% |
| Threads | 11 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 26-31 cores)</summary>

```
1789716696 31
1789716701 31
1789716706 31
1789716711 31
1789716716 31
1789716721 31
1789716726 31
1789716731 31
1789716736 31
1789716741 31
1789716746 31
1789716751 31
1789716756 31
1789716761 31
1789716766 31
1789716771 31
1789716776 31
1789716781 31
1789716786 26
1789716791 26
```
</details>

---

