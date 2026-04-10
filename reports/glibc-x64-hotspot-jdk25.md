---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-10 06:00:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 11 |
| Allocations | 421 |

<details>
<summary>CPU Timeline (3 unique values: 30-39 cores)</summary>

```
1775814858 39
1775814863 33
1775814868 33
1775814873 33
1775814878 33
1775814883 33
1775814888 33
1775814893 33
1775814898 33
1775814903 33
1775814908 33
1775814913 33
1775814918 30
1775814923 30
1775814928 30
1775814933 30
1775814938 30
1775814943 30
1775814948 30
1775814953 30
```
</details>

---

