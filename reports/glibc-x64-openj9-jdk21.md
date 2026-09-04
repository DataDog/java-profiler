---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-04 10:05:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 11 |
| Allocations | 391 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1788530482 96
1788530487 96
1788530492 96
1788530497 96
1788530502 96
1788530507 94
1788530512 94
1788530517 94
1788530522 94
1788530527 94
1788530532 94
1788530537 92
1788530542 92
1788530547 92
1788530552 94
1788530557 94
1788530562 94
1788530567 94
1788530572 94
1788530577 94
```
</details>

---

