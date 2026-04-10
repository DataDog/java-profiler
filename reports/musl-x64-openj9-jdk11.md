---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-10 06:00:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1059 |
| Sample Rate | 17.65/sec |
| Health Score | 1103% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 83-93 cores)</summary>

```
1775814836 83
1775814841 83
1775814846 85
1775814851 85
1775814856 85
1775814861 85
1775814866 85
1775814871 85
1775814876 85
1775814881 85
1775814886 85
1775814891 85
1775814896 85
1775814901 85
1775814906 85
1775814911 85
1775814916 85
1775814921 85
1775814926 89
1775814931 89
```
</details>

---

