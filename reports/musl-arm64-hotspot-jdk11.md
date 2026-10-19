---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-19 14:36:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 23-48 cores)</summary>

```
1792434703 23
1792434708 23
1792434713 23
1792434718 23
1792434723 23
1792434728 23
1792434733 23
1792434738 23
1792434743 23
1792434748 23
1792434753 23
1792434758 36
1792434763 36
1792434768 36
1792434773 36
1792434778 36
1792434783 36
1792434788 36
1792434793 36
1792434798 36
```
</details>

---

