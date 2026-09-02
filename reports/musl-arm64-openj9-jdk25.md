---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-02 09:15:24 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 294 |
| Sample Rate | 4.90/sec |
| Health Score | 306% |
| Threads | 12 |
| Allocations | 172 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1788354654 32
1788354659 32
1788354664 32
1788354669 32
1788354674 32
1788354679 32
1788354684 32
1788354689 32
1788354694 32
1788354699 32
1788354704 32
1788354709 32
1788354714 32
1788354719 32
1788354724 32
1788354729 32
1788354735 32
1788354740 32
1788354745 32
1788354750 32
```
</details>

---

