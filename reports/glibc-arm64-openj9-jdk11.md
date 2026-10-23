---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 09:42:11 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1008 |
| Sample Rate | 16.80/sec |
| Health Score | 1050% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 12-38 cores)</summary>

```
1792762572 14
1792762577 14
1792762582 12
1792762587 12
1792762592 12
1792762597 12
1792762602 12
1792762607 12
1792762612 12
1792762617 12
1792762622 12
1792762627 12
1792762632 36
1792762637 36
1792762642 36
1792762647 36
1792762652 38
1792762657 38
1792762662 38
1792762667 38
```
</details>

---

