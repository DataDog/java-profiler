---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-21 15:43:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 10 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (3 unique values: 13-48 cores)</summary>

```
1792611537 13
1792611542 13
1792611547 13
1792611552 13
1792611557 13
1792611562 13
1792611567 13
1792611572 13
1792611577 13
1792611582 48
1792611587 48
1792611592 48
1792611597 48
1792611602 48
1792611607 48
1792611612 48
1792611617 48
1792611622 48
1792611627 48
1792611632 48
```
</details>

---

