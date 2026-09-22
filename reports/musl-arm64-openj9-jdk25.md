---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 07:06:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1790074848 24
1790074853 24
1790074858 24
1790074863 24
1790074868 24
1790074873 24
1790074878 29
1790074883 29
1790074888 29
1790074893 29
1790074898 29
1790074903 29
1790074908 29
1790074913 29
1790074918 29
1790074923 29
1790074928 29
1790074933 29
1790074938 29
1790074943 29
```
</details>

---

