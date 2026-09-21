---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 09:40:56 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 10 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (4 unique values: 22-49 cores)</summary>

```
1789997711 40
1789997717 40
1789997722 40
1789997727 40
1789997732 40
1789997737 40
1789997742 40
1789997747 22
1789997752 22
1789997757 22
1789997762 22
1789997767 22
1789997772 22
1789997777 22
1789997782 22
1789997787 22
1789997792 22
1789997797 22
1789997802 22
1789997807 31
```
</details>

---

