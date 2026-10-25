---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-25 08:54:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 12 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 11-16 cores)</summary>

```
1792932527 16
1792932532 16
1792932537 16
1792932542 16
1792932547 16
1792932552 16
1792932557 16
1792932562 16
1792932567 16
1792932572 16
1792932577 16
1792932582 16
1792932587 11
1792932592 11
1792932597 11
1792932602 11
1792932607 11
1792932612 11
1792932617 11
1792932622 11
```
</details>

---

