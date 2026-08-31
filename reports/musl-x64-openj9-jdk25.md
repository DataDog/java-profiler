---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-30 21:22:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 11 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (3 unique values: 91-96 cores)</summary>

```
1788139088 96
1788139093 96
1788139098 96
1788139103 96
1788139108 96
1788139113 94
1788139118 94
1788139123 94
1788139128 94
1788139133 94
1788139138 94
1788139143 94
1788139148 94
1788139153 94
1788139158 96
1788139163 96
1788139168 96
1788139173 96
1788139178 96
1788139183 96
```
</details>

---

